let se = ReasonReact.stringToElement;

let searchedValuesCompFn value =>
  <li key=value onClick=(fun _ => Js.log ("Remove: " ^ value))> (se value) </li>;

let se = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent "Text";

let make ::title ::searchedValues _ => {
  ...component,
  render: fun _ =>
    <Aggregation title searchedValues searchedValuesCompFn> (fun x => <input />) </Aggregation>
};