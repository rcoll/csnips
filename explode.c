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

int main() {
	char **list;
	size_t i, len;
	explode( "a,bb,ccc,dddd,e,ff,ggg,hhhh,i,j,k,lll,mm,n", ",", &list, &len );

	printf( "%s\n", list[7] );

	for ( i = 0; i < len; ++i ) {
		free( list[i] );
	}

	free( list );
}

// EOF