type actions =
  | Increment
  | Decrement;

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => 0, /* here, state is an `int` */
  reducer:(action, state) =>
    switch action {
      | Increment => ReasonReact.Update(state + 1)
      | Decrement => ReasonReact.Update(state - 1)
    }
  ,
  render: ({state, reduce}) => <div>
    <div> (Utils.ste("From: " ++ (string_of_int(state)))) </div>
    <div> (Utils.ste("Limit: 10")) </div>
    <button onClick=(reduce((_) => Increment))> {ReasonReact.stringToElement("+")} </button>
    <button onClick=(reduce((_) => Decrement))> {ReasonReact.stringToElement("-")} </button>
    <QueryTodos from=state/>
    <MutateTodo />
  </div>
};


