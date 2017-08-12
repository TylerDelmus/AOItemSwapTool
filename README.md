# AO Item Swap Tool

When injected this DLL will allow you to get items you wouldn't normally be able to into containers. 

You will need to use a DLL injector such as Winject or Extreme Injector to inject this DLL into the Anarchy Online client.

I've only confirmed this DLL to work on the legacy client but in thoery it should also work on the new client.

The release build is using the v141 toolset so you WILL need the 2017 Runtimes which can be found here: https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads

### If you don't know what you're doing then you'll want to [download the pre-built version](https://github.com/TylerDelmus/AOItemSwapTool/files/1219557/AOItemSwapTool.zip) and then find a injector to inject the DLL into the client before trying the exploits below.

# The following exploits are possible with this DLL:


### Duplication Bag Creation
Required: 

* 1 Random Item
* 3 Backpacks
* 2 Characters

(Line the bags up in your inventory left to right so you can easily identify them)
1. Open all three bags.
2. Place a random item in bag 1
3. Grab bag 2 and right click on bag 1 (Bag 2 should pop into bag 1)
4. Place a random item in bag 3
5. Grab bag 1 and right click on bag 3 (Bag 1 should pop into bag 3)
6. Right click the bag that is inside of bag 3 to open it.
7. Give bag 3 (The one in your inventory) to the second character.
8. On the second character run to another zone that has a bank and then dig down and put the innermost bag in your bank.
9. Now back on the first character you can take the bag out of the container that is still up on your screen and place it in your bank.

At this point you should have a set of dupe bags linking two characters.

### How to use duplication bags
At this point the following criteria should be met:
* 2 Characters in different zones with a set of linked dupe bags
* The receiving character standing at a bank (Or owns a portable bank)
* The receiving character has it's dupe bag in the bank
* The sending character has it's dupe bag in it's inventory

1. On the sender: Open the dupe bag and place the items in
2. On the receiver: Take the dupe bag out of the bank, take all of the items out of it, and then place the dupe bag back in the bank.
3. On the sender: Take all of the items back out of the dupe bag

Both characters should now have a copy of the items.

### Nodrop trade
Required: 

* 1 Random Item
* 2 Backpacks
 
1. Place whatever you want to trade in bag 1
2. Place a random item in bag 2
3. Grab bag 1 and right click on bag 2 (Bag 1 should pop into bag 2)
4. Trade the bag in your inventory to the receiving party

If the bag contains nodrops you will need to drag the innermost bag into either your bank or back slot first.

#### - Tagyourit
