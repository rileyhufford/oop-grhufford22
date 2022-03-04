//console.log("hello");
export class Cord {
    constructor(length, connector, capacity) {
        super(ip);
        this._length = null;
        this.length = length;
        this._connector = null;
        this.connector = connector;
        this._capacity = null;
        this.capacity = capacity; //this.set capacity

    }

    //getters and setters ----------
    get length() { return this._length; }

    set length(value) {
        if (value > 0.0) this._length = value;
        else throw new RangeError("length must be positive");
    }

    get connector() { return this._connector; }

    set connector(value) {
        if (value.startsWith("male ") || value.startsWith("female ")) this._connector = value;
        else throw new RangeError("connector must be male or female");
        this._connector = value;
    }

    get capacity() { return this._capacity; }

    set capacity(value) {
        if (value > 0.0) this._capacity = value;
        else throw new RangeError("capacity must be positive");
    }

    //-----------------


    //cord.opposite
    get opposite() {
        if (this.connector.startsWith("male")) return "female" + this._connector.substring(4);
        else return "male" + this._connector.substring(6);
    }

    compatible(equipment) {
        return this.capacity >= equipment.consumption
            && this.opposite == equipment.connector;
    }
}

export class Device
{
    constructor(ip)
    {
        this._ip = ip;
    }
    api(json, callback)
    {
        console.log("sent" + JSON.stringify(json) + " to " + this._ip);
        setTimeout(()=>callback({'status': 200, 'response': json}), 100);
    }
}

//export class Fused
//{
//    constructor(fuseOk, fuseType)
//    {
//        this._fuseOk = fuseOk;
//        this._fuseType = fuseType;
//    }
//}



export class Fused extends Device
{
    constructor(ip, length, connector, capacity, fuseOk, fuseType)
        {
            super(ip, length, connector, capacity);
            this._fuseOk = fuseOk;
            this._fuseType = fuseType;
        }

    //mixin
    const Fused = {
        get fuseOk() {
            return this._fuseOk;
        },
        trip() {
            this._fuseOk = false;
        },
        reset() {
            this._fuseOk = true;
        },
    }
}

export class FusedCord extends Cord
{
    constructor(ip, length, connector, capacity, fuseOk, fuseType)
        {
            super(ip, length, connector, capacity);
            this._fuseOk = fuseOk;
            this._fuseType = fuseType;
        }
}

Object.assign(FusedCord.prototype, Fused); //does the same as the two lines below
//FusedCord.prototype.reset = Fused.prototype.reset;
//FusedCord.prototype.trip = Fused.prototype.trip;

let myCord = new FusedCord("127.0.0.1", 10, "male 3 prong", 20, true, "iso 3322");

myCord.reset();

console.log(`cord fuse ok: ${myCord.fuseOk}`);
//myCord.print = () => { console.log("printing");}
//myCord.print();


export class Equipment {
    constructor(consumption, connector, enabled) {
        this._consumption = consumption;
        this._connector = connector;
        this._enabled = enabled;
    }
}
