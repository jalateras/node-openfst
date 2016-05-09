'use strict'
const test = require('tape')

test('timing test', function (t) {
  t.equal(typeof Date.now, 'function')
  const FST = require('..')
  console.log('FST', FST)
  console.log('FST.hello', FST.hello())
  const fst = FST.Transducer()
  // // Adds state 0 to the initially empty FST and make it the start state.
  fst.addState()   // 1st state will be state 0 (returned by AddState)
  fst.setStart(0)  // arg is state ID

  // Adds two arcs exiting state 0.
  // Arc constructor args: ilabel, olabel, weight, dest state ID.
  fst.addArc(0, FST.Arc(1, 1, 0.5, 1))  // 1st arg is src state ID
  fst.addArc(0, FST.Arc(2, 2, 1.5, 1))

  // Adds state 1 and its arc.
  fst.addState()
  fst.addArc(1, FST.Arc(3, 3, 2.5, 2))

  // Adds state 2 and set its final weight.
  fst.addState()
  fst.setFinal(2, 3.5)  // 1st arg is state ID, 2nd arg weight
  t.end()
})
