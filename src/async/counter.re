type state = {
  count: int,
  timerId: option Js.Global.intervalId
};

let increaseCount _id {ReasonReact.state: state} =>
  ReasonReact.Update {...state, count: state.count + 1};

let component = ReasonReact.statefulComponent "Counter";

let make _children => {
  ...component,
  initialState: fun () => {count: 0, timerId: None},
  didMount: fun {state, update} =>
    ReasonReact.SilentUpdate {
      ...state,
      timerId: Some (Js.Global.setInterval (update increaseCount) 1000)
      /* if you're not used to currying, this form is clearer: */
      /* Js.Global.setInterval (fun id => self.update increaseCount id) */
    },
  render: fun {state} => <div> (ReasonReact.stringToElement (string_of_int state.count)) </div>
};
