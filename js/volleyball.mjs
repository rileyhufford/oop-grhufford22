//might switch to types of hats and have a second class called event
//idea is to see if the hat is suitable for a certain event
export class volleyball
{
    constructor(color, professional, inflated)
    {
        this._color = null;
        this.color = color;
        this._professional = null;
        this.professional = professional;
        this._inflated = null;
        this.inflated = inflated;
    }
    get color() {return this._color;}
    set color(value)
    {
        if(typeof value === 'string') 
        {
            this._color = value;
        }
        else throw new TypeError("Color must be type string");
    }

    get professional() {return this._professional;}
    set professional(value)
    {
        if(value == true || value == false)
        {
            this._professional = value;
        }
        else throw new TypeError("Professional must be type boolean");
    }

    get inflated() {return this._inflated;}
    set inflated(value)
    {
        if(value == true || value == false)
        {
            this._inflated = value;
        }
        else throw new TypeError("Inflated must be type boolean");
    }

}

