{-# LANGUAGE OverloadedStrings #-}

module Main where

import Control.Monad.Cont

import qualified Data.ByteString as B
import Network.Socket
import qualified Network.Socket.ByteString as B

dfltDest = tupleToHostAddress (127, 0, 0, 1)
dfltPort = 4321

main = withSocketsDo $ do
            -- Create the socket
            sock <- socket AF_INET Datagram 0

            -- Bind
            let addr = SockAddrInet dfltPort dfltDest
            bind sock addr

            -- Receive a message
            putStrLn "Awaiting 3 messages:"
            forM_ [1,2,3] $ \_ -> do
                resp <- B.recv sock 8192
                putStr "  Received \""
                B.putStr resp
                putStrLn "\""

            -- Close the socket
            close sock
