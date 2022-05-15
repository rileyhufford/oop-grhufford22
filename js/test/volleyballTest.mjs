import { baseballhat } from "../cord.mjs";
import {assert, expect, should} from 'chai';

describe('Volleyball', ()=>{
    describe('length', ()=>{
      it('is the first constructor parameter ',()=>{
        const cord = new Cord(1,"male plug",3);
        expect(cord.length).to.equal(1); //nice to use expect (over assert) because it is easier
        //                                 to read for more nontechnial people
      })
      it('can be changed',()=>{
        const cord = new Cord(1,"male plug",3);
        cord.length = 2.5;
        expect(cord.length).to.equal(2.5);
      })
      it('must be positive',()=>{
        const cord = new Cord(1,"male plug",3);
        const expectArg = ()=>{cord.length = 0.0}; //lambda expression to call itself or something
        expect(expectArg)
          .to.throw("length must be positive")
      });
    }); //describe length
  }); // describe Cord