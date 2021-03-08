# CreativeEmbeddedSystemsHW3

This project is a touch-activated treat dispenser for my dog Chewy. It uses the current time of day to estimate how many calories he's eaten so far based on his typical meal schedule. If he hasn't met his caloric needs for the day, a treat will be dispensed when he activates the sensor. If he has, no treat will be dispensed. Every time Chewy interacts with the dispenser it's logged in the terminal so I can keep track. With a small tweak to the code this dispenser can be easily customized for your dog. 

Component List:
-ESP32 
-Breadboard and extender for the ESP32
-Several M-M wires
-A servo motor
-A cardboard box large enough to fit all of the hardware
-A medicine bottle or similarly shaped container
-Tape
-Paper
-Tin Foil
-9 volt battery and connector to power the ESP32
-A laptop

The arduino code uses a M-M wire plugged into the ESP32's GPIO 4 as a touch sensor. I wrapped the (non-plugged in) pin of the wire in tin foil to increase the size of the touch pad. Since tin foil is conductive, touching anywhere on the foil will register. 
The servo motor should be plugged into GPIO15, ground, and 5V. 
The .ino code should be uploaded to the ESP32 and then the ESP32 should be plugged into the battery and powered wirelessly. The Python code should be run on a laptop on the same wifi network as the ESP32. 
In order to construct the actual dispenser, begin by drilling a treat-sized hole in the bottom of the medicine bottle. Roll a piece of paper into a uniform tube shape as wide as the hole and insert it into the hole so it's through the bottle and sticks out of the hole by ~1cm. Cut a hole the size of the bottle in your cardboard box so that the medicine bottle rests on top of the box with the tube poking in a small amount. Insert the hardware into the box and place the servo motor (with a piece of cardboard the size and shape of the hole taped to the wing) directly under the hole, taping it in place such that the paper tube in the medicine bottle rests on top of the cardboard on the Servo. Cut a hole in the bottom of the box to allow a treat to fall through. Photos are included below for reference. 

The dispenser is loaded by inserting treats into the paper tube. When the touch sensor is activated, the servo moves, unblocking the tube and allowing a treat to fall out. 

In order to customize the program for your dog, change the value of max_cals in the Python code. This is what sets the maximum number of calories allowed per day and ensures your dog can't overconsume treats with this tool and become sick. Chewy is a small dog and only requires 400 calories per day. Larger dogs will need more. 

![IMG_0766](https://user-images.githubusercontent.com/43915800/110008936-537fad80-7cea-11eb-9bcc-6c7791620427.jpg)
![IMG_0767](https://user-images.githubusercontent.com/43915800/110008951-567a9e00-7cea-11eb-949a-48fa6b63a25b.jpg)
![IMG_0765](https://user-images.githubusercontent.com/43915800/110008992-62666000-7cea-11eb-8eb9-800f322200d6.jpg)
