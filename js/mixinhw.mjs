export class Camera
{
    constructor(mount, CfocalLength)
    {
        this._mount = mount;
        this._CfocalLength = CfocalLength;
    }
}

export class Lens extends Camera
{
    constructor(mount, focalLength)
    {
        super(mount);
        this._focalLength = null;
        this.focalLength = focalLength;
    }
    
    get focalLength()
    {
        return this._focalLength;
    }

    set focalLength(value)
    {
        if(value > 0) this._focalLength = value;
        else throw new RangeError("focal length cannot be zero or less than")
    }
}

export class ConnectedLens extends Camera
{
    getLensPowered()
    {
        return this._lensPowered;
    }

    lensConnectionError()
    {
        this._lensPowered = false;
    }

    reset()
    {
        this._lensPowered = true;
    }
}

export class Body extends Lens
{
    constructor(mount, CfocalLength, mirrorless, lensPowered)
    {
        super(mount, CfocalLength);
        this._mirrorless = mirrorless;
        this._lensPowered = lensPowered;
    }
}

function mixin(target, ...src)
{
    for(let mixed of src)
    {
        for(var property of Object.getOwnPropertyNames(mixed.prototype))
        {
            if(property != 'constructor')
            {
                target.prototype[property] = mixed.prototype[property]
            }
        }
    }
}

mixin(Body, ConnectedLens);

let myCamera = new Body("ef", 85, false, true);

//connected testing
myCamera.lensConnectionError();
console.log(`connected status(error, should return false): ${myCamera.getLensPowered()}`);
myCamera.reset();
console.log(`connected status(reset, should return true): ${myCamera.getLensPowered()}`);

console.log(`myCamera is type Body: ${myCamera instanceof Body}`);
console.log(`myCamera is type lens: ${myCamera instanceof Lens}`);
console.log(`myCamera is type camera: ${myCamera instanceof Camera}`);
console.log(`myCamera is type connected(should be false): ${myCamera instanceof ConnectedLens}`);
//^ returns false as it should, because it is not an instance of ConnectedLens.
//But can use it's methods


export default
{
    Camera,
    ConnectedLens,
    Body 
}
