uid_test1=setuid_test
uid_test2=seteuid_test
uid_test3=uid_drop_test


#echo -e "\n\nchown root:root..."
#echo "special perm: 0 (none)"
#echo 1 | sudo -S chown root:root $uid_test1
#echo 1 | sudo -S chown root:root $uid_test2
#echo 1 | sudo -S chmod 0755 $uid_test1
#echo 1 | sudo -S chmod 0755 $uid_test2
#ls -la | grep $uid_test1
#ls -la | grep $uid_test2
#(./$uid_test1 1000)
#(./$uid_test2 1000)
#(./$uid_test1 1001)
#(./$uid_test2 1001)
#(./$uid_test1 0)
#(./$uid_test2 0)

#echo -e "\n\nchown root:root..."
#echo -e "\n\nspecial perm: 1 (sticky-bit)"
#echo 1 | sudo -S chown root:root $uid_test1
#echo 1 | sudo -S chown root:root $uid_test2
#echo 1 | sudo -S chmod 1755 $uid_test1
#echo 1 | sudo -S chmod 1755 $uid_test2
#ls -la | grep $uid_test1
#ls -la | grep $uid_test2
#(./$uid_test1 1000)
#(./$uid_test2 1000)
#(./$uid_test1 1001)
#(./$uid_test2 1001)
#(./$uid_test1 0)
#(./$uid_test2 0)
#
#echo -e "\n\nspecial perm: 2 (setgid)"
#echo 1 | sudo -S chown root:root $uid_test1
#echo 1 | sudo -S chown root:root $uid_test2
#echo 1 | sudo -S chmod 2755 $uid_test1
#echo 1 | sudo -S chmod 2755 $uid_test2
#ls -la | grep $uid_test1
#ls -la | grep $uid_test2
#(./$uid_test1 1000)
#(./$uid_test2 1000)
#(./$uid_test1 1001)
#(./$uid_test2 1001)
#(./$uid_test1 0)
#(./$uid_test2 0)

echo -e "\n\nspecial perm: 4 (setuid)"
echo 1 | sudo -S chown root:root $uid_test1
echo 1 | sudo -S chown root:root $uid_test2
echo 1 | sudo -S chown root:root $uid_test3
echo 1 | sudo -S chmod 4755 $uid_test1
echo 1 | sudo -S chmod 4755 $uid_test2
echo 1 | sudo -S chmod 4755 $uid_test3
ls -la | grep $uid_test1
ls -la | grep $uid_test2
ls -la | grep $uid_test3
(./$uid_test1 1000)
(./$uid_test2 1000)
(./$uid_test3 1000)
(./$uid_test1 1001)
(./$uid_test2 1001)
(./$uid_test3 1001)
(./$uid_test1 0)
(./$uid_test2 0)
(./$uid_test3 0)


#echo -e "\n\nchown a:a + special perm: 4 (setuid)"
#echo 1 | sudo -S chown a:a $uid_test1
#echo 1 | sudo -S chown a:a $uid_test2
#echo 1 | sudo -S chown a:a $uid_test3
#echo 1 | sudo -S chmod 4755 $uid_test1
#echo 1 | sudo -S chmod 4755 $uid_test2
#echo 1 | sudo -S chmod 4755 $uid_test3
#ls -la | grep $uid_test1
#ls -la | grep $uid_test2
#ls -la | grep $uid_test3
#(./$uid_test1 1000)
#(./$uid_test2 1000)
#(./$uid_test3 1000)
#(./$uid_test1 1001)
#(./$uid_test2 1001)
#(./$uid_test3 1001)
#(./$uid_test1 0)
#(./$uid_test2 0)
#(./$uid_test3 0)
#
##
#echo -e "\n\nchown guest:guest + special perm: 4 (setuid)"
#echo 1 | sudo -S chown guest:guest $uid_test1
#echo 1 | sudo -S chown guest:guest $uid_test2
#echo 1 | sudo -S chown guest:guest $uid_test3
#echo 1 | sudo -S chmod 4755 $uid_test1
#echo 1 | sudo -S chmod 4755 $uid_test2
#echo 1 | sudo -S chmod 4755 $uid_test3
#ls -la | grep $uid_test1
#ls -la | grep $uid_test2
#ls -la | grep $uid_test3
#(./$uid_test1 1000)
#(./$uid_test2 1000)
#(./$uid_test3 1000)
#(./$uid_test1 1001)
#(./$uid_test2 1001)
#(./$uid_test3 1001)
#(./$uid_test1 0)
#(./$uid_test2 0)
#(./$uid_test3 0)
