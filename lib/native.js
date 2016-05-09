'use strict'

const isDebug = !!parseInt(process.env.OPENFST_DEBUG)
const configName = isDebug ? 'Debug' : 'Release'
const native = require('../build/' + configName + '/openfst')

module.exports = native
module.exports.isDebug = isDebug
