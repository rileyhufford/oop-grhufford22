import time 

class Camera():
    def __init__(self, brand, mount, price):
        self.brand = brand
        self.mount = mount
        self.price = price

    #getters
    def get_brand(self):
        return self.brand

    def get_mount(self):
        return self.mount

    def get_price(self):
        return self.price

class Lens(Camera):
    def __init__(self, brand, mount, price, focalLength):
        super().__init__(brand, mount, price)
        self.focalLength = focalLength

    #getters
    def get_brand(self):
        return self.brand

    def get_mount(self):
        return self.mount

    def get_price(self):
        return self.price
    
    def get_focalLength(self):
        return self.focalLength
    

class Body(Camera):
    def __init__(self, brand, mount, price, name):
        super().__init__(brand, mount, price)
        self.name = name

    #getters
    def get_brand(self):
        return self.brand

    def get_mount(self):
        return self.mount

    def get_price(self):
        return self.price
    
    def get_name(self):
        return self.name

#compatiable lens and body
def compatiable(lens, body):
    return (lens == body)

#Lens Inventory
lensInv = {}
def lensInvAdd(brand, mount):
    if(isinstance(brand, str) and isinstance(mount, str)):
        lensInv.update({brand : mount})
    else:
        raise Exception("Brand and mount must be a string!")

bodyInv = {}
def bodyInvAdd(brand, mount):
    if(isinstance(brand, str) and isinstance(mount, str)):
        bodyInv.update({brand: mount})
    else:
        raise Exception("Brand and mount msy be a string!")


#default inventory filling:
def lensInvFill():
    lens = Lens("canon", "ef", 1000.99, 10)
    lens2 = Lens("canon", "ef-s", 190.12, 14)
    lens3 = Lens("sony", "e-mount", 100.24, 24)
    lens4 = Lens("panasonic", "r", 550.99, 100)

    lensInvAdd((lens.brand + " " + str(lens.focalLength) + "mm"),("mount type: " + lens.mount))
    lensInvAdd((lens2.brand+ " " + str(lens2.focalLength) + "mm"),("mount type: " +  lens2.mount))
    lensInvAdd((lens3.brand+ " " + str(lens3.focalLength) + "mm"),("mount type: " +  lens3.mount))
    lensInvAdd((lens4.brand+ " " + str(lens4.focalLength) + "mm"),("mount type: " +  lens4.mount))

def bodyInvFill():
    body = Body("canon", "ef", 100.99, "90d")
    body2 = Body("canon", "ef-s", 492.12, "sl3")
    body3 = Body("sony", "e-mount", 100.24, "a7")
    body4 = Body("fuji", "e", 340.24, "film")

    bodyInvAdd((body.brand + " " + body.name),("mount type: " + body.mount))
    bodyInvAdd((body2.brand+ " " + body2.name),("mount type: " +  body2.mount))
    bodyInvAdd((body3.brand+ " " + body3.name),("mount type: " +  body3.mount))
    bodyInvAdd((body4.brand+ " " + body4.name),("mount type: " +  body4.mount))

#sorting inventories based on 
def compatiableSort(lensInv, bodyInv):
    print("\n")
    for i in lensInv:
        for j in bodyInv:
            if(compatiable(lensInv.get(i),bodyInv.get(j))):
                print(j, "compatiable with", i)


#User input paths:
def usrAddLens():
    print("enter brand:")
    brand = str(input())
    print("enter mount:")
    mount = str(input())
    print("enter price:")
    price = float(input())
    print("enter focal length:")
    focalLength = int(input())
    usrLens = Lens(brand, mount, price, focalLength)
    lensInvAdd((usrLens.brand+ " " + str(usrLens.focalLength) + "mm"),("mount type: " +  usrLens.mount))
    print("\nLens added to inventory!\nNew lens inventory: ")
    print(lensInv)
    print("\n")
    while True:
        usr = input()
        if(usr == "y"):
            main()
        elif(usr == "n"):
            break
        else:
            print("Enter 'y' for yes and 'n' for no")


def usrAddBody():
    print("enter brand:")
    brand = str(input())
    print("enter mount:")
    mount = str(input())
    print("enter price:")
    price = int(input())
    print("enter name of body:")
    name = str(input())
    usrBody = Body(brand, mount, price, name)
    bodyInvAdd((usrBody.brand + " " + usrBody.name),("mount type: " + usrBody.mount))
    print("\nBody added to inventory!\nNew body inventory: ")
    print(bodyInv)
    print("\n")
    usr = print("Would you like to return to the menu(y/n)?")
    while True:
        usr = input()
        if(usr == "y"):
            main()
        elif(usr == "n"):
            break
        else:
            print("Enter 'y' for yes and 'n' for no")


def main():
    #default inventory fill
    lensInvFill()
    bodyInvFill()

    #user input
    while True:
        print("Welcome to Riley's camera store inventory manager!")
        print("‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n")
        print("To see the current inventory of the store type: 'show inventory'\n")
        print("To add a lens to the inventory type: 'add lens'")
        print("To add a body to the inventory type: 'add body'\n")
        print("To see current compatiable lens' and bodys' type: 'compatiable inventory'\n")
        print("To exit type: exit")
        usr = str(input()).lower()

        if(usr == "add lens"):
            usrAddLens()
            break

        elif(usr == "add body"):
            usrAddBody()
            break
        elif(usr == "exit"):
            break
        elif(usr == "compatiable inventory"):
            compatiableSort(lensInv, bodyInv)
            while True:
                print("\nWould you like to return to the menu(y/n)?")
                usr2 = input()

                if(usr2 == "y"):
                    main()
                elif(usr2 == "n"):
                    break
                else:
                    print("Enter 'y' for yes and 'n' for no")
        elif(usr == "show inventory"):
            print("Lens inventory:")
            print(lensInv)
            print("\n\nBody inventory:")
            print(bodyInv)
            print("\nWould you like to return to the menu(y/n)?")
            usr2 = input()

            if(usr2 == "y"):
                main()
            elif(usr2 == "n"):
                break
            else:
                print("Enter 'y' for yes and 'n' for no")
        else:
            print("Please enter one of the following choices:\n")
            time.sleep(2)
        

if __name__ == "__main__":
    main()

