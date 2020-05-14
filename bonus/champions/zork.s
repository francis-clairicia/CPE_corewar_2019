#
# Zork champion for CoreWar
#
# By Bob Dylan
#
# Tue May 12 00:00:00 2020
#

.name "Zork"
.comment "Just a basic living command"

sti r1,%:live,%1
and r1 ,%0, r1
live: live %1
zjmp %:live