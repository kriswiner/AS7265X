Overview
	
	This document explains the functionalities of three different .bin files in AS7265 firmware update.


Changes in pin configrations

	In AS7265x generation 2, the INT and SLV_RST1 pin are swapped on default (dynamic configuration: can be withdrawn with special configuration). The existing Moonlight hardware 1V1 (or older) don't consider this new pinning. Therefore a special firmare exists for the existing Moonlight hardware 1Vx. This special firmwware is in this folder under the name "AS7265_complete_moonlight.bin". Please note, use this firmware only in combination with the old Moonlight hardware generation 1 (1Vx).

	For newer hardware designs of ams or customized designs which considers the pin swapping, please use the binarry fils .bon without extension "_moonlight"

	Note, the difference between the firmware generation 1 and 2 is only the pin swapping.

Supported firmware files

	User has to choose the firmware .bin file based on the methode of update and hardware
	
	* AS7265_complete.bin file should be used while updating the firmware through FlashCat Software.
	* AS7265_update.bin file should be used while updating the firmware through DashBoard or UPDATE GUI. In order to use the GUI for updating the firmware, the hardware should have firmware version 11.0.0 or above.
	* It is required to change the I²C to UART mode in case of using the UPDATER GUI-
	* AS7265_complete_moonlight.bin file should be used for updating Hardware 1V1 Moonlight device using FlashCat Software.

