" Vim syntax file
" Language:     C Squared
" Author:       Noor Wachid
" URL:          https://github.com/noorwachid/vim-gularen/

if exists("b:current_syntax")
	finish
endif

" Inlines
syn match csqComment "# .*$" 
syn keyword csqKeyword const var refer move
syn keyword csqKeyword func return null
syn keyword csqKeyword class struct operate mutate get set
syn keyword csqKeyword enum 

syn match csqType "\<[A-Z][A-Za-z0-9_]*\>" 
syn match csqFunction "\<[a-z_][A-Za-z0-9_]*("me=e-1
syn match csqFunction "\<[a-z_][A-Za-z0-9_]*<"me=e-1

syn match csqNumber "\<[0-9\.]\+\>"
syn region csqString start='"' end='"'

hi def link csqComment Comment
hi def link csqKeyword Keyword
hi def link csqType Type
hi def link csqFunction Function
hi def link csqString String
hi def link csqNumber Number

let b:current_syntax = "csq"
