[@bs.module] external gql : ReasonApolloTypes.gql = "graphql-tag";

/* Write graphql query passing a limit as variable */
let query = [@bs] gql({|
    query getTodos($from: Int, $limit: Int) {
      todos(from: $from, limit: $limit) {
        id
        name
      }
    }
  |});

/* Describe the result type */
type todo = {. "name": string, "id": string};
type data = {. "todos": array(todo)};


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
  type variables = {. "limit": int, "from": int};
};

/*
  Pass the configuration to the Apollo Client
  You can now use `FetchTodos` as a JSX tag
*/
module FetchTodos = Apollo.Client.Query(Config);

let component = ReasonReact.statelessComponent("App");

let make = (~from, _children) => {
...component,
render: (_self) => {
  let variables = {
    "from": from,
    "limit": limit
  };
  <FetchTodos query variables>
    ((response) => {
      switch response {
         | Loading => <div> (Utils.ste("Loading")) </div>
         | Failed(error) => <div> (Utils.ste(error)) </div>
         | Loaded(result) =>{
          <div>
          (
            ReasonReact.arrayToElement(
              Array.map(((todo) => <div key=(todo##id)> (Utils.ste(todo##name))</div>), result##todos)
            )
          )
          </div>
         }
      };
    })
  </FetchTodos>
}

};


