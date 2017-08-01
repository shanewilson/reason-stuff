let se = ReasonReact.stringToElement;

let buckets: list Aggregation.bucket = [
  {key: "blue", doc_count: 2},
  {key: "c", doc_count: 3},
  {key: "aa", doc_count: 2},
  {key: "ac", doc_count: 3},
  {key: "bb", doc_count: 2},
  {key: "cc", doc_count: 3}
];

let searchedValues: list Aggregation.bucket = [{key: "a", doc_count: 1}];

let searchedValuesLoc = ["chr13:123123-123123", "chr7:23432423-*"];

ReactDOMRe.renderToElementWithId
  <div style=(ReactDOMRe.Style.make width::"250px" ())>
    <Terms title="Projects" buckets>
      (
        fun (bucket: Aggregation.bucket) =>
          <li key=bucket.key onClick=(fun _ => Js.log ("Add: " ^ bucket.key))>
            (se bucket.key)
            (se " - ")
            (se (string_of_int bucket.doc_count))
          </li>
      )
    </Terms>
    <Text title="Location" searchedValues=searchedValuesLoc />
    <Text title="Boop" searchedValues=[] />
  </div>
  "index";