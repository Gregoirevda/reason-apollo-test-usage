/*
  Pass the configuration to the Apollo Client
  You can now use `FetchTodos` as a JSX tag
*/
module DeleteTodo = Apollo.Client.Mutation(MutateTodoConfig);

let component = ReasonReact.statelessComponent("App");

let make = (_children) => {
  ...component,
  render: (_self) => {
    let variables = {
      "id": "uuid-1"
    };
    <DeleteTodo>
      ((deleteTodo, result) => {
          let mutationResponse = switch result {
            | NotCalled => <div>  (Utils.ste("Not Called")) </div>
            | Loading => <div> (Utils.ste("Loading")) </div>
            | Loaded(response) => <div> (Utils.ste(response##deleteTodo##name ++ " deleted")) </div>
            | Failed(error) => <div> (Utils.ste(error)) </div>
          };
        <div>
          <button onClick=((_mouseEvent) => deleteTodo(~variables, ()))> (Utils.ste("Delete Todo")) </button>
          <div> (mutationResponse) </div>
        </div>
      })
    </DeleteTodo>
  }
};

















