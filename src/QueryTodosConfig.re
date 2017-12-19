/* Describe the result type */
type todo = {. "name": string, "id": string};
type data = {. "todos": array(todo)};
type responseType = data;

/* Optional: Define the type of variables you give
   We also have a `from` variable coming from the props
 */
type variables = {. "limit": int, "from": int};
