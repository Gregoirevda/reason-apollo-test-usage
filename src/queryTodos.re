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

/*
  Pass the configuration to the Apollo Client
  You can now use `FetchTodos` as a JSX tag
*/
module FetchTodos = Apollo.Client.Query(QueryTodosConfig);

let component = ReasonReact.statelessComponent("App");

let make = (~from, _children) => {
...component,
render: (_self) => {
  let variables = {
    "from": from, /* from comes from the props */
    "limit": 10
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


