// vi:nu:et:sts=4 ts=4 sw=4

// Lifted from Lemon, part of Sqlite which is Public Domain.


/* The text in the input is part of the argument to an %ifdef or %ifndef.
** Evaluate the text as a boolean expression.  Return true or false.
*/
static 
int 	    PreprocEvalBoolean (
    char        *z, 
    int         lineno
)
{
    int		    neg = 0;
    int         res = 0;
    int         okTerm = 1;
    int         i;

    for(i=0; z[i]!=0; i++) {
        if( ISSPACE(z[i]) ) 
            continue;
        // !term
        if( z[i]=='!' ) {
            if( !okTerm ) 
                goto pp_syntax_error;
            neg = !neg;
            continue;
        }
        // term || term
        if( z[i]=='|' && z[i+1]=='|' ) {
            if( okTerm ) 
                goto pp_syntax_error;
            if ( res ) 
                return 1;
            i++;
            okTerm = 1;
            continue;
        }
        // term && term
        if( z[i]=='&' && z[i+1]=='&' ) {
            if( okTerm ) 
                goto pp_syntax_error;
            if( !res ) 
                return 0;
            i++;
            okTerm = 1;
            continue;
        }
        // ( terms )
        if( z[i]=='(' ) {
            int         k;
            int         n = 1;

            if( !okTerm ) 
                goto pp_syntax_error;
            for(k=i+1; z[k]; k++){
                if( z[k]==')' ){
                    n--;
                    if( n==0 ){
                        z[k] = 0;
                        res = PreprocEvalBoolean(&z[i+1], -1);
                        z[k] = ')';
                        if( res<0 ){
                            i = i-res;
                            goto pp_syntax_error;
                        }
                        i = k;
                        break;
                    }
                }else if( z[k]=='(' ){
                    n++;
                }else if( z[k]==0 ){
                    i = k;
                    goto pp_syntax_error;
                }
            }
            if( neg ){
                res = !res;
                neg = 0;
            }
            okTerm = 0;
            continue;
        }
        // term := (bool)found 
        if( ISALPHA(z[i]) ){
            int         j, k, n;

            if( !okTerm ) 
                goto pp_syntax_error;
            for(k=i+1; ISALNUM(z[k]) || z[k]=='_'; k++){}
            n = k - i;

            // Search the defines to see if the one that we scanned exists.
            res = 0;
            for (j=0; j<nDefine; j++){
                if ((strncmp(azDefine[j],&z[i],n) == 0) && (azDefine[j][n] == 0)) {
                    res = 1;        // We found the define
                    break;
                }
            }
            i = k-1;
            if( neg ){
                res = !res;
                neg = 0;
            }
            okTerm = 0;
            continue;
        }
        goto pp_syntax_error;
    }
    return res;

pp_syntax_error:
    if( lineno>0 ){
        fprintf(stderr, "%%if syntax error on line %d.\n", lineno);
        fprintf(stderr, "  %.*s <-- syntax error here\n", i+1, z);
        exit(1);
    }else{
        return -(i+1);
    }
}



/* Run the preprocessor over the input file text.  The global variables
** azDefine[0] through azDefine[nDefine-1] contains the names of all defined
** macros.  This routine looks for "%ifdef" and "%ifndef" and "%endif" and
** comments them out.  Text in between is also commented out as appropriate.
*/
static 
void PreprocInput(char *z){
    int         i, j, k;
    int         exclude = 0;
    int         start = 0;
    int         lineno = 1;
    int         start_lineno = 1;

    // Scan line 1 char at a time until NUL-terminator.
    for(i=0; z[i]; i++){
        if( z[i]=='\n' ) 
            lineno++;
        if ((z[i] != '%') || ((i > 0) && (z[i-1] != '\n')) ) 
            continue;
        if ((strncmp(&z[i],"%endif",6) == 0) && ISSPACE(z[i+6]) ){
            if (exclude) {
                exclude--;
                if (exclude == 0) {
                    // Blank out all data from 0 to i.
                    for(j=start; j<i; j++) {
                        if (z[j] != '\n') 
                            z[j] = ' ';
                    }
                }
            }
            // Blank out from i until NUL-terminator.
            for(j=i; (z[j] && (z[j] != '\n')); j++) 
                z[j] = ' ';
        }else if( strncmp(&z[i],"%else",5)==0 && ISSPACE(z[i+5]) ){
            if( exclude==1){
                exclude = 0;
                for(j=start; j<i; j++) if( z[j]!='\n' ) 
                    z[j] = ' ';
            }else if( exclude==0 ){
                exclude = 1;
                start = i;
                start_lineno = lineno;
            }
            for(j=i; z[j] && z[j]!='\n'; j++) 
                z[j] = ' ';
        }else if( strncmp(&z[i],"%ifdef ",7)==0 
            || strncmp(&z[i],"%if ",4)==0
            || strncmp(&z[i],"%ifndef ",8)==0 ){
            if( exclude ){
                exclude++;
            }else{
                int         isNot;
                int         iBool;
                for(j=i; z[j] && !ISSPACE(z[j]); j++){}
                iBool = j;
                isNot = (j==i+7);
                while( z[j] && z[j]!='\n' ){ 
                    j++; 
                }
                k = z[j];
                z[j] = 0;
                exclude = PreprocEvalBoolean(&z[iBool], lineno);
                z[j] = k;
                if( !isNot ) 
                    exclude = !exclude;
                if( exclude ){
                    start = i;
                    start_lineno = lineno;
                }
            }
            for(j=i; z[j] && z[j]!='\n'; j++) 
                z[j] = ' ';
        }
    }
    if( exclude ){
        fprintf(stderr,"unterminated %%ifdef starting on line %d\n", start_lineno);
        exit(1);
    }
}




