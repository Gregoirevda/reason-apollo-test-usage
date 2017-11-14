// graphql-tools combines a schema string with resolvers.
const {makeExecutableSchema} = require('graphql-tools');

// Construct a schema, using GraphQL schema language
const typeDefs = `
	type Todo {
		name: String!
		id: ID!
	}

  type Query {
    todos(limit: Int): [Todo]
  }
`;

// Provide resolver functions for your schema fields
const resolvers = {
  Query: {
    todos: (_,{limit = 10}) => {
      console.log('limit', limit);
      return [{
        id: "uuid-1",
        name: 'Todo 1'
      },
      {
        id: "uuid-2",
        name: 'Todo 2'
      },
      {
        id: "uuid-3",
        name: 'Todo 3'
      }]
      .filter((_, index) => index < limit);
    }
  }
};

exports.schema = makeExecutableSchema({
  typeDefs,
  resolvers,
});

