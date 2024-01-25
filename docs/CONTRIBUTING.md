<!-- markdownlint-disable-next-line MD043 -->
# Code style

## DO

- use `snake_case` for functions and variables
- prefix CV64-specific functions and global variables with `cv64_`
- use common abbreviations to shorten names - see [abbreviations](#abbreviations)
- follow this scheme for member function and variable names

<!-- markdownlint-disable-next-line MD040 -->
```
<prefix>_<membertype>_<functionname/variablename>
```

Some examples of this are:

- `cv64_ovl_konamilogo_check_btn_press`
- `cv64_ovl_konamilogo_funcs`
- `cv64_dl_fade_with_outline`

## DON'T

- mix different casing (i.e. `snake_case_camelCase`)

## Abbreviations

These are some common abbreviations we should strive to use ubiquitously in the project.
This table should be updated with new abbreviations as we discover more useful ones.

| Word/Phrase  | Abbreviation |
| ------------ | ------------ |
| display list | dl           |
| function     | func         |
| header       | hdr          |
| info         | inf          |
| manager      | mgr          |
| object       | obj          |
| system       | sys          |
