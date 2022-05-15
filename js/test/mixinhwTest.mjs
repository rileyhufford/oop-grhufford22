import {Camera, Lens} from '../mixinhw.mjs'

import {assert, expect, should} from 'chai';

describe('Lens', ()=>{
    describe('mount', ()=>{
        it('is the first constructor parameter ', ()=>{
            const lens = new Lens("ef", 24)
            expect(lens.mount).to.equal("ef");
        });
    });
});

describe('Lens', ()=>{
    describe('focalLength', ()=>{
        it('is the second constructor parameter ', ()=>{
            const lens = new Lens("ef", 24)
            expect(lens.focalLength).to.equal(24);
        })
        it('can be changed', ()=>{
            const lens = new Lens("ef", 24);
            lens.focalLength = 50;
            expect(lens.focalLength).to.equal(50);
        })
        it('must be positive', ()=>{
            const lens = new Lens("ef", 24);
            expect(()=>{lens.focalLength = 0}).to.throw("focal length must be positive")
        });
    });
});