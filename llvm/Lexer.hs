module Lexer where

import Text.Parsec.String (Parser)
import Text.Parsec.Language (emtpyDef)

import qualified Text.Parsec.Token as Tok

lexer :: Tok.TokenParser ()
lexer = Tok.makeTokenParser style
   where
      ops = ["'", "#", "%"]
      names = ["push", "jmp", "label", "halt", "pop", "cmp", "je", "sub", "add"]
      styles = emptyDef {
           Tok.commentLine = ";"
         , Tok.reservedOpNames = ops
         , Tok.reservedNames = names
         }
