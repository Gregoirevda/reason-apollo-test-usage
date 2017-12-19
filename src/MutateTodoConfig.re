/* Describe the result type */
type todo = {. "name": string, "id": string};
type data = {. "deleteTodo": todo};
type responseType = data;

/* Optional: Define the type of variables you give
   We also have a `from` variable coming from the props
 */
type variables = {.
  "id": string
};
