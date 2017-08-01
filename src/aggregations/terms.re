let se = ReasonReact.stringToElement;

let searchedValuesCompFn (bucket: Aggregation.bucket) =>
  <li key=bucket.key onClick=(fun _ => Js.log ("Remove: " ^ bucket.key))>
    (se bucket.key)
    (se " :: ")
    (se (string_of_int bucket.doc_count))
  </li>;

let se = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent "Terms";

let make
    ::title
    ::buckets
    ::searchedValues=[]
    ::bucketListLimit=5
    ::noDataMessage=(se "No data found for this field.")
    children => {
  ...component,
  render: fun _ => {
    let needsSearch = List.length buckets > bucketListLimit;
    let hasData = List.length searchedValues + List.length buckets > 0;
    <Aggregation title searchedValues searchedValuesCompFn needsSearch>
      (
        fun state => {
          let bs =
            List.filter
              (
                fun (bucket: Aggregation.bucket) =>
                  state.query == "" || Js.String.includes state.query bucket.key
              )
              buckets;
          <Aggregation.NoData hasData noDataMessage>
            <Aggregation.ComponentList compFn=children.(0) values=bs />
          </Aggregation.NoData>
        }
      )
    </Aggregation>
  }
};