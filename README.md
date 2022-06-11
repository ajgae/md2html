# md2html - a simple C utility to convert Markdown to HTML

## Roadmap

- [x] read file into memory (with fixed maximum for now)
- [x] scaffolding for clean program (separate init, exec)
- [ ] basic conversion

## Markdown rules

*This* is the beginning of a paragraph
which is continued **here**.

This is a new paragraph. Italics and bold text *do not...

... carry across* paragraphs, titles or list elements.

- [ ] paragraphs
  - insert a space instead of a `\n` between lines in the same
    paragraph
  - two lines mark the separation between paragraph and previous/next
    element
- [ ] horizontal rule
  - three or more asterisks, dashes or underscodes on their own line
  - must be separated above and below by an empty line
- [ ] titles (no alternate == or -- syntax)
  - must be separated above and below by an empty line
- [ ] italicized *text*
  - does not carry across paragraphs / different elements (titles,
    etc.)
  - issue a warning if started and not finished by the end of the
    paragraph / title
- [ ] bold **text**
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

