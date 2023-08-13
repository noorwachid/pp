" Vim syntax file
" Language:     ++
" Author:       Noor Wachid
" URL:          https://github.com/noorwachid/vim-gularen/

if exists("b:current_syntax")
	finish
endif

" Inlines
syn match ppComment "# .*$" 
syn keyword ppKeyword const var refer move as
syn keyword ppKeyword func return
syn keyword ppKeyword namespace use class struct operate mutate virtualize override get set
syn keyword ppKeyword enum 
syn keyword ppKeyword false true null
syn keyword ppKeyword if else switch case default for in

syn match ppType "\<[A-Z][A-Za-z0-9_]*\>" 
syn match ppFunction "\<[a-z_][A-Za-z0-9_]*("me=e-1
syn match ppFunction "\<[a-z_][A-Za-z0-9_]*<"me=e-1

syn match ppNumber "\<[0-9\.]\+\>"
syn region ppString start='"' end='"'

hi def link ppComment Comment
hi def link ppKeyword Keyword
hi def link ppType Type
hi def link ppFunction Function
hi def link ppString String
hi def link ppNumber Number

let b:current_syntax = "pp"
