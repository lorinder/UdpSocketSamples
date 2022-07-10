{-# LANGUAGE OverloadedStrings #-}

module Main where

import Control.Concurrent
import Control.Monad.Cont

import qualified Data.ByteString.UTF8 as U8B
import qualified Data.ByteString as B
import Network.Socket
import qualified Network.Socket.ByteString as B

addr = tupleToHostAddress (127, 0, 0, 1)
port = 4321

main = withSocketsDo $ do
    -- Create the socket
    sock <- socket AF_INET Datagram 0

    -- Send a datagram
    let sa = SockAddrInet port addr
    putStrLn "Sending 3 messages:"
    forM_ [1,2,3] $ \i -> do
        let msg = "Hi, there " ++ show i
        putStrLn $ "  Sending message \"" ++ msg ++ "\""
        B.sendTo sock (U8B.fromString msg) sa
        threadDelay 1000000
    putStrLn "Done."

    -- Close the socket
    close sock
