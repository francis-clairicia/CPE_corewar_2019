#
# Zork champion for CoreWar
#
# By Bob Dylan
#
# Tue May 12 00:00:00 2020
#

.name	"Zork"
.comment "Just a basic living command"

sti r1,%:live,%1      # Store my playeer number at the live instruction
and r1 ,%0, r1        # Set the carry to true
live: live %1         # Say I'm alive
zjmp %:live           # Jump to the live command