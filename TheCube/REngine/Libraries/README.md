# Subprojects

## Linking

Subrojects are set variables of the form:

```
set (SubprojectName "ProjectName")
set (Library_REngine_${SubprojectName} "${LibraryName}" PARENT_SCOPE)
```

which are linked to the REngine library:

```
target_link_libraries ("${Library_REngine_Core}"
  PUBLIC
    "${Library_REngine_Base}"
)
```

The REnginie library itself sets a variable `re_var_Library_REngine`:

```
set (re_var_Library_REngine "${Library_REngine}" PARENT_SCOPE)
```

which executable targets should link to:

```
target_link_libraries ("${ProjectName}"
	"${re_var_Library_REngine}" # Defined in the REngine library
)
```
