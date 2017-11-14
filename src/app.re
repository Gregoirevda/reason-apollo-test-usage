[@bs.module] external gql : ReasonApolloTypes.gql = "graphql-tag";



/* Write graphql query passing a limit as variable */
let query = [@bs] gql({|
    query getTodos($limit: Int) {
      todos(limit: $limit) {
        id
        name
      }
    }
  |});

/* Describe the result type */
type todo = {. "name": string, "id": string};
type data = {. "todos": array(todo)};


/* Optional: define variables for your query */
let variables = {
  "limit": 2
};

/*
 Create a module containing:
 `responseType` (type of the response)
 `variables` (can have no value if ommited, but needs to be declared!)
 */
module Config = {
  type responseType = data;
  type variables = {. "limit": int};
};

/*
  Pass the configuration to the Apollo Client
  You can now use `FetchTodos` as a JSX tag
*/
module FetchTodos = Apollo.Client(Config);

let component = ReasonReact.statelessComponent("App");

let make = (_children) => {...component, render: (_self) =>
<FetchTodos query variables>
  ((response) => {
    switch response##loading {
       | true => <div> (Utils.ste("Loading")) </div>
       | false => {
        <div>
        (
          ReasonReact.arrayToElement(
            Array.map(((todo) => <div key=(todo##id)> (Utils.ste(todo##name))</div>), response##data##todos)
          )
        )
        </div>
       }
    };
  })
</FetchTodos>
};


