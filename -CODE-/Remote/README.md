# Remote

## Contents

[.\\FlashingTheRemote--works\\](.\\FlashingTheRemote--works\\)</br>
The code on the remote.

[.\\FlashTest--works\\](.\\FlashTest--works\\)</br>
Used for testing if the remote can be flashed.</br>
Also used for other shenanigans.

[.\\IrDecode\\](.\\IrDecode\\)</br>
Code that should use the TSOP382 sensor to decode RC5 signals.

[.\\TheGitRepo\\](.\\TheGitRepo\\)</br>
A copy of the repo this project is based on (out project is just a slightly modified copy).

## Connecting hardware 

1. connect jumper wire to your arduino uno for the spi standard

| Arduino pin | Spi name | Spi position  |
| :---------- | :------- | :-----------  |
| 12          | MISO     | 1 (Left top)  |
| 13          | SCK      | 3 (Left mid)  |
| 10          | Reset    | 5 (Left bot)  |
| 5V          | Vcc      | 2 (Right top) |
| 11          | MOSI     | 4 (Right mid) |
| Gnd         | GND      | 6 (Right bot) |

2. Connect the newly created spi cable to the remote spi connector

3. Connect the arduino uno to your machine.

> [!NOTE]  
> It is recomended to pull out batteries out of the remote before this, but i'm not your mom to tell you what to do.

> [!NOTE]  
> You can do this :3.

> [!NOTE]  
> Sources: Trust me, i guess.

> [!IMPORTANT]
> This is written unseriously, but that adds character.

> [!CAUTION]
> Someone should check this.
> - [ ] Peer reviewed status <!--replace "[ ]" with "[x]" after review-->


<!--
> [!NOTE]  
> Highlights information that users should take into account, even when skimming.

> [!TIP]
> Optional information to help a user be more successful.

> [!IMPORTANT]  
> Crucial information necessary for users to succeed.

> [!WARNING]  
> Critical content demanding immediate user attention due to potential risks.

> [!CAUTION]
> Negative potential consequences of an action.
-->
