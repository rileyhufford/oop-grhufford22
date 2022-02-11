//might switch to types of hats and have a second class called event
//idea is to see if the hat is suitable for a certain event
export class baseballhat
{
    constructor(mainColor, type, strapType)
    {
        this._mainColor = null;
        this.mainColor = mainColor;
        this._type = null;
        this.type = type;
        this._strapType = null;
        this.strapType = strapType;
    }
    get mainColor() {return this._mainColor;}
    set mainColor(value)
    {

    }

    get type() {return this._type;}
    set type(value)
    {

    }

    get strapType() {return this._strapType;}
    set strapType(value)
    {

    }

}

