# Upload testing code

This code can be on the remote.

Just compile and upload using platformio and the attached platformio.ini and avrdude.conf files.</br>
(This means you just open tis in vscode with platformio and press "upload")
> [!TIP]
> Slightly more about these two files can be found in [README_FlashingTheRemote.html](..\\README_FlashingTheRemote.html) one dir above. It's more of a guide on how to get them.


Make sure you have the hardware connected correctly
> [!TIP]
> read "[README.md](../README.md)" in the above directory

This platformio.ini also has a way to upload a backup code (same as the real code) from a hex file. Involves changing which of the last non-empty lines is not commented out. We have no use for this now.
