console.log("hello");
class Cord
{
    _constructor_(length, connector, capacity)
    {
        this._length = length;
        this._connector = connector;
        this._capacity = capacity;

    }

    get connector() {return this._connector;}
    
    set connector(value)
    {
        if (value.startsWith("male ") || value.startsWith("female ")) this._connector = value;
        else throw RangeError('connector must be male or female');
        this._connector = value;
    }

    //cord.opposite
    get opposite()
    {
        if (this.connector.startsWith("male")) return "female" + this._connector.substring(4);
        else return "male" + this._connector.substring(6);
    }

    compatible(equipment)
    {
        return this.capacity >= equipment.consumption 
        && this.opposite == equipment.connector;
    }
}

class Equipment
{
    __constructor__(consumption, connector, enabled)
    {
        this._consumption = consumption;
        this._connector = connector;
        this._enabled = enabled;
    }
}