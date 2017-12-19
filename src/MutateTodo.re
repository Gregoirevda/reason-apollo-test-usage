[@bs.module] external gql : ReasonApolloTypes.gql = "graphql-tag";

/* Write graphql query passing a limit as variable */
let mutation = [@bs] gql({|
    mutation deleteTodo($id: ID!) {
      deleteTodo(id: $id) {
        id
        name
      }
    }
  |});

/* Describe the result type */
type todo = {. "name": string, "id": string};
type data = {. "deleteTodo": todo};


/* Optional: define variables for your query */
let limit = 2;

/*
 Create a module containing:
 `responseType` (type of the response)
 `variables` (can have no value if ommited, but needs to be declared!)
 */
module Config = {
  type responseType = data;
  /* Optional: Define the type of variables you give
     We also have a `from` variable coming from the props
   */
  type variables = {.
    "id": string
  };
};

/*
  Pass the configuration to the Apollo Client
  You can now use `FetchTodos` as a JSX tag
*/
module DeleteTodo = Apollo.Client.Mutation(Config);


let component = ReasonReact.statelessComponent("App");

let make = (_children) => {
  ...component,
  render: (_self) => {
    let variables = {
      "id": "uuid-1"
    };
    <DeleteTodo mutation>
      ((deleteTodo, result) => {
          let mutationResponse = switch result {
            | NotCalled => <div/>
            | Loading => <div> (Utils.ste("Loading")) </div>
            | Loaded(response) => {
              Js.log(response##deleteTodo);
              <div> (Utils.ste("response")) </div>
            }
            | Failed(error) => <div> (Utils.ste(error)) </div>
          };
        <div>
          <div> (mutationResponse) </div>
          <button onClick=((_mouseEvent) => deleteTodo(~variables, ()))> (Utils.ste("Delete Todo")) </button>
        </div>
      })
    </DeleteTodo>
  }
};

















