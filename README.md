# md2html - a simple C utility to convert Markdown to HTML

## Roadmap

- [x] read file into memory
- [x] scaffolding for clean program (separate init, exec)
- [x] basic conversion
- [ ] implement more rules

***
## Markdown rules
This is the beginning of a paragraph
which is continued **here**.

This is a new paragraph. Italics and bold text *do not...

... carry across* paragraphs, titles or list elements.

####### There are more than six '#' here

- [x] paragraphs
  - insert a space instead of a `\n` between lines in the same
    paragraph
  - two lines mark the separation between paragraph and previous/next
    element
- [x] horizontal rule
  - three or more asterisks, dashes or underscodes on their own line
  - must be separated above and below by an empty line
- [x] titles (no alternate == or -- syntax)
  - must be separated above and below by an empty line
- [x] italicized *text*
  - does not carry across paragraphs / different elements (titles,
    etc.)
  - issue a warning if started and not finished by the end of the
    paragraph / title
- [x] bold **text**
  - see notes about italicized text
- [ ] inline code 
  - [ ] `simple`
  - [ ] ``with `backticks` included``
  - see notes about italicized text
- [ ] blockquotes
  - can contain multiple paragraphs; lines between paragraphs should
    then start with `>`, or multiple blockquote elements will be
    created (one for each paragraph)
  - must be separated above and below by an empty line
- [ ] links
  - look like this: `[Text](https://example.com)`
  - text simply enclosed in braces e.g. `[Text]` not followed by
    parentheses should not be counted as link; how?
- [ ] lists
  - [ ] unordered
  - [ ] ordered
  - [ ] with sublists

