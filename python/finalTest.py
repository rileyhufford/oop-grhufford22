from cgi import print_arguments
import sys

sys.path.append(".")
import final
from final import Camera, Body, Lens

def test_Camera(brand, mount, price):
    test = final.Camera(brand, mount, price)
    assert(test.brand == brand)
    assert(test.mount == mount)
    assert(test.price == price)

    print("Camera assertions passed!")

def test_Body(brand, mount, price, name):
    test = final.Body(brand, mount, price, name)
    assert(test.brand == brand)
    assert(test.mount == mount)
    assert(test.price == price)
    assert(test.name == name)

    print("Body assertions passed!")

def test_Lens(brand, mount, price, focalLength):
    test = final.Lens(brand, mount, price, focalLength)
    assert(test.brand == brand)
    assert(test.mount == mount)
    assert(test.price == price)
    assert(test.focalLength == focalLength)

    print("Lens assertions passed!")

def test_compatiable(lens, body):
    assert(final.compatiable(lens.mount, body.mount))

    print("Compatiable assertion passed!")