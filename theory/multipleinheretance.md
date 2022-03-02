FusedCord extends Cord

What if Fused was a class?

FusedCord extends Cord and Fused

Saying this is saying you have two base classes. 
You "are" a Cord and you "are" Fused.
Languages that support this support multiiple inheretance.

Most languages don't support this.
It's because of "diamond of death"

Say you had Device as a class.
    - IP address

Fused extends Device
    - fuseType
    - fuseOk

Cord extends Device as well