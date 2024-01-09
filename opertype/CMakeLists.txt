# Sadie's Anope Modules (C) 2016-2024 Sadie Powell
# SPDX-License-Identifier: GPL-2.0-only

build_modules(${CMAKE_CURRENT_SOURCE_DIR})

install(FILES "opertype.example.conf" DESTINATION ${CONF_DIR})
