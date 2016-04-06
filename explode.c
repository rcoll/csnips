#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strdup( const char *src ) {
	char *tmp = malloc( strlen( src ) + 1 );
	
	if ( tmp ) {
		strcpy( tmp, src );
	}

	return tmp;
}

void explode( const char *src, const char *tokens, char ***list, size_t *len ) {   
	if ( src == NULL || list == NULL || len == NULL ) {
		return;
	}

	char *str, *copy, **_list = NULL, **tmp;
	*list = NULL;
	*len = 0;

	copy = strdup( src );
	if ( copy == NULL ) {
		return;
	}

	str = strtok( copy, tokens );
	if ( str == NULL ) {
		goto free_and_exit;
	}

	_list = realloc( NULL, sizeof *_list );
	if ( _list == NULL ) {
		goto free_and_exit;
	}

	_list[*len] = strdup( str );
	if ( _list[*len] == NULL ) {
		goto free_and_exit;
	}
	( *len )++;

	while ( ( str = strtok( NULL, tokens ) ) ) {   
		tmp = realloc( _list, ( sizeof *_list ) * ( *len + 1 ) );
		if ( tmp == NULL ) {
			goto free_and_exit;
		}

		_list = tmp;

		_list[*len] = strdup( str );
		if ( _list[*len] == NULL ) {
			goto free_and_exit;
		}
		( *len )++;
	}

	free_and_exit:
	*list = _list;
	free( copy );
}

/**
 * Main function, for demonstration purposes only.
 * Omit this function if you are copying this and using as a lib.
 */
int main() {
	// Initialize some variables
	char **list;
	size_t i, len;

	// Run the explode function pointed at our string
	explode( "a,bb,ccc,dddd,e,ff,ggg,hhhh,i,j,k,lll,mm,n", ",", &list, &len );

	// Print out a few k/vs
	printf( "Index 0: %s\n", list[0] );
	printf( "Index 5: %s\n", list[5] );
	printf( "Index 3: %s\n", list[3] );
	printf( "Index 7: %s\n", list[7] );

	// Free memory from the list keys
	for ( i = 0; i < len; ++i ) {
		free( list[i] );
	}

	// Free memory from the list var
	free( list );
}

// EOF