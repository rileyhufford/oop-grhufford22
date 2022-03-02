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
    private bool m_fuseOk; (not allowed in an interface)
        - In Javescript can only promise what it can have, not actually do
    - getFuseType()
    - setFuseType()
    - isFuseOk()

Cord extends Device as well
    - capacity (max amps)

FusedCord extends Cord and Fused
    - Problem is FusedCord is Device twice;
    once through Cord and once through Fused.

Solutions to this problem:
    1. Don't allow it, single inheretance only
        Javascript -> mixin instead
        Jave -> interfaces instead
    2. Do allow it. Then you have to have some way to be a Device only once.
        C++ uses "virtual base classes" to straighten this out.

