//console.log("hello");

export class DeviceObserver{
    deviceNotification(device, bulletin) {}
}

export class Logger extends DeviceObserver
{
    constructor()
    {
        super();
        this._deviceNotifications = new Array();
    }
    deviceNotifications(device, bulletin)
    {
        this._deviceNotifications.push({'device':device, 'bulletin': bulletin});
        console.log("log "+ device + ": " + JSON.stringify(bulletin));
    }
}

export const logger = new Logger();

export class Device extends DeviceObserver {
    constructor(ip) {
        super();
        this._ip = ip;
        this._observers = new Array();
        this._postponements = new Array();
        this._notifying = false;
        this.addObserver(logger);
    }

    toString()
    {
        return `$(this._ip)`
    }

    _removeObserver(observer)
    {
        for(let i = 0; i<this._observers.length; ++i)
        {
            if (this._observers[i] === observer)
            {
                this._observers.splice(i,1);
            }
        }
    }


    removeObserver(observer)
    {
        if (this._notifying){
            this._postponements.push(() => {this.removeObserver(observer);});
            return; 
        }
        for (let i=0; i< this._observers.length; ++i) {
            if(this._observers[i] === observer) {
                this._observers.splice(i,1);
            }
        }
    }

    _addObserver(observer)
    {
        this._removeObserver(observer);
        this._observers.push(observer);
    }

    addObserver(observer)
    {
        if (this._notifying){
            this._postponements.push(() => {this.removeObserver(observer);});
            return; 
        }
        this.removeObserver(observer);
        this._observers.push(observer);
    }

    _notify(bulletin) {
        this._notifying = true;
        this._observers.forEach((observer)=> observer.deviceNotification(this, bulletin));
        for(;;) {
            const postponements = this._postponements;
            if (postponements.length == 0) break;
            this._postponements = new Array();
            postponements.forEach((postponements) => {postponement();});
        }
        this._notifying = false;
    }


    api(json, callback) {
        console.log("sent " + JSON.stringify(json) + " to " + this._ip);
        setTimeout(()=>callback({ 'status': 200, 'response': json}), 100);
    }
}

export class Cord extends Device{
    constructor(ip, length, connector, capacity) {
        super(ip);
        this._length = null;
        this.length = length;
        this._connector = null;
        this.connector = connector;
        this._capacity = null;
        this.capacity = capacity; //this.set capacity
        this._powersDevice = null;
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
        //this._connector = value;
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

    unplug()
    {
        if (this._powersDevice != null)
        {
            this._notify({'action':'unplug', 'target': this._powersDevice});
            this._powersDevice = null;
        }
    }

    power(device)
    {
        if(this._powersDevice != device)
        {
            this.unplug();
            this._notify({'action':'will-power', 'target':device});
            this._powersDevice = device;
            this._notify({'action':'power', 'target':device});
        }
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
    getFuseOk() {
        return this._fuseOk;
    }
    setFuseOk(value)
    {
        if (value != this._fuseOk)
        {
            this._notify({'action':'will-set-fuse-ok', 'target':value});
            this._powersDevice = device;
            this._notify({'action':'set-fuse-ok', 'target':device});
        }
    }
    trip() {
        this._setFuseOk(false);
    }
    reset() {
        this._setFuseOk(true);
    }
}

export class FusedCord extends Cord
{
    constructor(ip, length, connector, capacity, fuseOk, fuseType)
        {
            super(ip, length, connector, capacity);
            this._fuseOk = fuseOk;
            this._fuseType = fuseType;
            this.addObserver(this);
        }

        deviceNotification(device, bulletin)
        {
            if (this._powersDevice != null && device === this &&
                 bulletin['action'] == 'will-set-fuse-ok' &&
                 bulletin['target'] == false)
             {
                 this._wasPluggedTo = this._powersDevice;
                 this.unplug();
             }

             if (this._wasPluggedTo != null && device === this &&
                bulletin['action'] == 'will-set-fuse-ok' &&
                bulletin['target'] == true)
            {
                this.power(this._wasPluggedTo)
                this._wasPluggedTo = this._powersDevice;
                this.unplug();
            }
        }
}

//mixin
function mixin(target, ...src) {
    for (let mixed of src) {
        for (var property of Object.getOwnPropertyNames(mixed.prototype)) {
            if (property != 'constructor') {
                target.prototype[property] = mixed.prototype[property]
            }
        }
    }
}


mixin(FusedCord, Fused);

//Object.assign(FusedCord.prototype, Fused); //does the same as the two lines below
//FusedCord.prototype.reset = Fused.prototype.reset;
//FusedCord.prototype.trip = Fused.prototype.trip;

let myCord = new FusedCord("127.0.0.1", 10, "male 3 prong", 20, true, "iso 3322");

myCord.reset();

myCord.fuseOk;

console.log(myCord.getFuseOk());

console.log(`fused cord is fusedcord: ${myCord instanceof FusedCord}`);
console.log(`fused cord is cord: ${myCord instanceof Cord}`);
console.log(`fused cord is device: ${myCord instanceof Device}`);
console.log(`fused cord is fused: ${myCord instanceof Fused}`);
//myCord.print = () => { console.log("printing");}
//myCord.print();


export class Equipment {
    constructor(ip, consumption, connector, enabled) {
        super(ip);
        this._consumption = consumption;
        this._connector = connector;
        this._enabled = enabled;
    }
    deviceNotification(device, bulletin)
    {
        console.log("got notification from" + device + ": " + JSON.stringify(bulletin));
    }
}

export default {
    Cord,
    Fused,
    FusedCord,
    Equipment
}