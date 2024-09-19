<!-- markdownlint-disable-next-line MD043 -->
# Code style

## DO

- use `PascalCase` for types
- use the format `TypeName_MethodName` for public methods on a type
- use the format `TypeName_methodName` (notice the lowercase "m") for private (static) methods on a
  type
- use the format `TypeName_VarName` for public variables
- use `snake_case` for method/function-local variables, translation-unit private variables,
  and type member variables
- use common abbreviations to shorten names - see [abbreviations](#abbreviations)

Some examples of this are:

- `OvlKonamiLogo_CheckBtnPress`
- `OvlKonamiLogo_Funcs`
- `dl_fade_with_outline`

## DON'T

- mix different casing (i.e. `snake_case_camelCase`)

## Abbreviations

These are some common abbreviations we should strive to use ubiquitously in the project.
This table should be updated with new abbreviations as we discover more useful ones.

| Word/Phrase   | Abbreviation |
| ------------- | ------------ |
| angle         | ang          |
| block         | blk          |
| button        | btn          |
| configuration | cfg          |
| display list  | dl           |
| function      | func         |
| graphic(s)    | gfx          |
| header        | hdr          |
| info          | inf          |
| manager       | mgr          |
| object        | obj          |
| overlay       | ovl          |
| system        | sys          |
