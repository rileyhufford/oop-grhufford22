# Final project: Camera store inventory manager
## General overview
For this project I made a hierarchy of objects using Python to create a way to manage camera components in a store. The classes I created are the following: Camera(top of the hierarchy), Lens(extends camera), and Body(extends camera). Lens and Body are the two main classes that are sellable products in the store. The Camera class holds the variables: brand, mount, and price that the Lens and Body classes both inherit.

The compatiable function is used to check the compatiablilty between a lens and body using the mount variable of each object. A lens and body are compatiable if they have the same mount.

The lensInvAdd and bodyInvAdd are both functions that use user input to add a Lens object and Body object respectively. These functions are called from the user input functions below.

The lensInvFill and bodyInvFill are both functions used to add default objects to each inventory dictonary to have some inital inventory.

The compatiableSort function is used sort between the two inventories and print out which body and lens combo would be possible with the current inventory. This is done using the compatiable function previously mentioned.

Main contains the start of user input and can be looped back to from other functions that use user input.

## User guide

To use this program, launch it using python3 and follow the instructions on screen. The page of the program is the menu and contains all of the different options of this inventory management system. 

On the main menu:
To see the current inventory of lenses and bodys type: 'show inventory'
To add a lens to the inventory type: 'add lens'
To add a body to the inventory type: 'add body'
To see current compatiable lens' and bodys' type: 'compatiable inventory'
To exit type: exit

When adding a lens or body: follow the on screen instructions and type in each variable one at a time.

If you would like to continue after any of the main menu selections type 'y' when prompted after using a feature. If you would like to exit on this screen type 'n'.