type bucket = {key: string, doc_count: int};

type state = {query: string, isCollapsed: bool, isSearching: bool};

let valueFromEvent evt :string => (evt |> ReactEventRe.Form.target |> ReactDOMRe.domElementToObj)##value;

let se = ReasonReact.stringToElement;

let component = ReasonReact.statefulComponent "Aggregation";

module AggregationHeader = {
  let component = ReasonReact.statelessComponent "AggregationHeader";
  let make ::active children => {
    ...component,
    render: fun _ =>
      <div
        style=(
          ReactDOMRe.Style.make
            backgroundColor::"#fcfcfc"
            padding::"0.5rem 1rem"
            color::(active ? "green" : "black")
            ()
        )>
        (children |> ReasonReact.arrayToElement)
      </div>
  };
};

module Arrow = {
  let component = ReasonReact.statelessComponent "Arrow";
  let make ::isCollapsed _children => {
    ...component,
    render: fun _ => <span> (se (isCollapsed ? "V" : ">")) </span>
  };
};

module Title = {
  let component = ReasonReact.statelessComponent "Title";
  let make ::title _children => {...component, render: fun _ => <span> (se title) </span>};
};

module ResetIcon = {
  let component = ReasonReact.statelessComponent "ResetIcon";
  let make ::visible ::onClick _children => {
    ...component,
    render: fun _ => visible ? <span onClick> (se "Reset") </span> : ReasonReact.nullElement
  };
};

module SearchIcon = {
  let component = ReasonReact.statelessComponent "SearchIcon";
  let make ::visible ::active ::onClick _children => {
    ...component,
    render: fun _ =>
      visible ?
        <span style=(ReactDOMRe.Style.make color::(active ? "green" : "black") ()) onClick>
          (se "Search")
        </span> :
        ReasonReact.nullElement
  };
};

module AggregationBody = {
  let component = ReasonReact.statelessComponent "AggregationBody";
  let make children => {
    ...component,
    render: fun _ => <div> (children |> ReasonReact.arrayToElement) </div>
  };
};

module SearchInput = {
  let component = ReasonReact.statelessComponent "FilterInput";
  let make ::active ::query ::handleOnChange _children => {
    ...component,
    render: fun _ =>
      active ?
        <input
          value=query
          _type="text"
          placeholder="Write something to do"
          onChange=handleOnChange
        /> :
        ReasonReact.nullElement
  };
};

module Collapsible = {
  let component = ReasonReact.statelessComponent "Collapsible";
  let make ::isCollapsed children => {
    ...component,
    render: fun _ =>
      <div> (isCollapsed ? ReasonReact.nullElement : children |> ReasonReact.arrayToElement) </div>
  };
};

module NoData = {
  let component = ReasonReact.statelessComponent "NoData";
  let make ::hasData ::noDataMessage=ReasonReact.nullElement children => {
    ...component,
    render: fun _ =>
      <div> (hasData ? children |> ReasonReact.arrayToElement : noDataMessage) </div>
  };
};

module ComponentList = {
  let component = ReasonReact.statelessComponent "ComponentList";
  let make ::values=[] ::compFn _children => {
    ...component,
    render: fun _ =>
      <ul> (List.map compFn values |> Array.of_list |> ReasonReact.arrayToElement) </ul>
  };
};

let make ::title ::needsSearch=false ::searchedValues=? ::searchedValuesCompFn=? children => {
  ...component,
  initialState: fun () => {query: "", isCollapsed: false, isSearching: false},
  render: fun {state, update} => {
    let hasSearchedValues =
      switch searchedValues {
      | Some _ => true
      | None => false
      };
    <div>
      <AggregationHeader active=hasSearchedValues>
        <span
          onClick=(
            update (
              fun _ {state} => ReasonReact.Update {...state, isCollapsed: not state.isCollapsed}
            )
          )>
          <Arrow isCollapsed=state.isCollapsed />
          <Title title />
        </span>
        <ResetIcon visible=hasSearchedValues onClick=(fun _ => Js.log "reset") />
        <SearchIcon
          visible=(needsSearch && not state.isCollapsed)
          active=state.isSearching
          onClick=(
            update (
              fun _ {state} => ReasonReact.Update {...state, isSearching: not state.isSearching}
            )
          )
        />
      </AggregationHeader>
      <AggregationBody>
        <SearchInput
          active=(state.isSearching && not state.isCollapsed)
          query=state.query
          handleOnChange=(
            update (fun evt _ => ReasonReact.Update {...state, query: valueFromEvent evt})
          )
        />
        <NoData hasData=hasSearchedValues>
          (
            switch (searchedValues, searchedValuesCompFn) {
            | (Some v, Some fn) => <ComponentList compFn=fn values=v />
            | _ => ReasonReact.nullElement
            }
          )
        </NoData>
        <Collapsible isCollapsed=state.isCollapsed> (children.(0) state) </Collapsible>
      </AggregationBody>
    </div>
  }
};