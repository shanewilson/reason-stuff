module.exports = {
  components: 'src/aggregations/**/*.re',
  resolver: function(x) { console.log(x)},
  webpackConfig: {
    module: {
      loaders: [
        // Set up Reason and OCaml files to use the loader
        { test: /\.(re|ml)$/, loader: 'bs-loader' },
      ]
    },
    resolve: {
      // Add .re and .ml to the list of extensions webpack recognizes
      extensions: ['.re', '.ml', '.js']
    }
  }
};