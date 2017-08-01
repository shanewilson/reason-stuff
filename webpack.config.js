const path = require('path');

module.exports = {
  entry: {
    aggregations: './lib/js/src/aggregations/root.js',
    async: './lib/js/src/async/counterRoot.js',
    simple: './lib/js/src/simple/simpleRoot.js',
    logo: './lib/js/src/logo/logoRoot.js',
    todomvc: './lib/js/src/todomvc/app.js',
    interop: './src/interop/interopRoot.js',
    retainedProps: './lib/js/src/retainedProps/retainedPropsRoot.js',
  },
  output: {
    path: path.join(__dirname, "bundledOutputs"),
    filename: '[name].js',
  },
};
