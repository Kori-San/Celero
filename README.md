# Celero
Celero, an Accelerometer based game for a MSP-430F5529LP used with a Educational BoosterPack MKII, developped with C-Language on Energia.
Here is a Trailer where you can see the game : https://youtu.be/4avW_mNNpvk.

## Celero is a game based with the Accelerometer available on the Educational BoosterPack MKII fused with a MSP-430F5529LP.
All the pins used are put on variables so if you're using another pack and / or another MCU then you could just remplace the pins to make it works.

## The game include only one level but multiple customization :
- Color customization for the player's character (Choose your own color between 6 colors)
- Option to manage maniability (You can adjust maniability and therefore change the difficulty of the game)
- Scores menu (Challenge your friends so you can keep the "Best Time" and "Best Death Counter" on the Score menu)

## How the game works
You begin in the Top Left corner of the Map and need to use the accelerometer to go in the Green Area (Named Victory Zone)
Each time you hit the screen limit or an obstacle you come back to the Top Left zone 
Be carefull because the position of the accelerometer is saved when you die, so you will a hard time going in the green zone each time you die.
After comming in the Victory zone you will have a Game Over screen who will display the number of deaths and the time of the current gaming session

### If you find any bug or if you have ideas to make the script better don't mind writting in the "Issues" section :)
