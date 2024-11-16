#include <Arduino.h>
#include <pmw_out.h>
#include <driver/rmt.h>

#define PWM_PIN 4                    // GPIO pin pro čtení PWM
#define RMT_RX_CHANNEL RMT_CHANNEL_0 // RMT kanál pro příjem
#define RMT_CLK_DIV 80               // Dělič hodin RMT (1 tick = 1 µs)
#define PULSE_MAX_VALID 2300
#define IDLE_TRESHOLD (PULSE_MAX_VALID + 500) 

void setup()
{
  // PWM output initialization
  pwmTask_Init();

  Serial.begin(115200);
  Serial.println("Initialized!");

  // Nastavení RMT pro příjem
  rmt_config_t rmt_rx;
  rmt_rx.channel = RMT_RX_CHANNEL;
  rmt_rx.gpio_num = (gpio_num_t)PWM_PIN;
  rmt_rx.clk_div = RMT_CLK_DIV; // Frekvence hodin (APB_CLK / 80 = 1 MHz -> 1 tick = 1 µs)
  rmt_rx.mem_block_num = 1;
  rmt_rx.rmt_mode = RMT_MODE_RX;
  rmt_rx.rx_config.filter_en = true;
  rmt_rx.rx_config.filter_ticks_thresh = 100; // Filtr pro pulzy kratší než 100 µs
  rmt_rx.rx_config.idle_threshold = IDLE_TRESHOLD;     // Idle threshold (v mikrosekundách)

  // Inicializace RMT a spuštění driveru
  rmt_config(&rmt_rx);
  rmt_driver_install(rmt_rx.channel, 1000, 0);

  // Aktivace příjmu RMT
  rmt_rx_start(RMT_RX_CHANNEL, true);
}

void loop()
{

  // Buffer pro uložení pulzů
  RingbufHandle_t rb = NULL; // RMT využívá ring buffer pro uložení přijatých pulzů
  rmt_get_ringbuf_handle(RMT_RX_CHANNEL, &rb);

  if (rb)
  {
    // Čtení položek z ring bufferu
    size_t numItems = 0;
    rmt_item32_t *items = (rmt_item32_t *)xRingbufferReceive(rb, &numItems, 1000);
        if (items)
        {
          // Ověření, že máme alespoň dvě položky (jednu HIGH a jednu LOW)
          if (numItems >= 2)
          {
            uint32_t high_time = items[0].duration0; // Délka pulzu HIGH
            uint32_t low_time = items[1].duration0;  // Délka pulzu LOW
            uint32_t period = high_time + low_time;  // Celková perioda PWM signálu

            // Výpočet střídavého poměru PWM signálu
            float duty_cycle = (high_time * 100.0) / period;

            Serial.println(duty_cycle);
          }

          // Uvolnění bufferu
          vRingbufferReturnItem(rb, (void *)items);
        }
  }

  //delay(500);
}
