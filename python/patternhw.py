# Singleton pattern: allows you to create one instance of a class. Benefits of singleton pattern
# To limit concurrent access to a shared resource.
# To create a global point of access for a resource.
# To create just one instance of a class, throughout the lifetime of a program.

#Classic singleton pattern that will only create a new instance if there isn't ome already

class Confluence(object):
    def __new__(self):
        if not hasattr(self, 'instance'):
            self.instance = super(Confluence, self).__new__(self)
        return self.instance

def test_building(a, b):
    assert((a is b) == True)
    print("Assertion passed")

def main():
    building = Confluence()
    building_2 = Confluence()

    test_building(building, building_2)

if __name__ == "__main__":
    main()