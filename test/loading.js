'use strict';

const expect = require('chai').expect;

describe('Native module',function(){

  it("should load properly", function() {
    const native = require('..');
    expect(native).to.exist;
  });

});

