#ifndef _DB_MYSQL_DIFFSQLGEN_GRANT_H_
#define _DB_MYSQL_DIFFSQLGEN_GRANT_H_

#include "grtpp_module_cpp.h"
#include "grts/structs.db.mysql.h"
#include "db_mysql_params.h"

static std::string get_type_str_for_grant(const db_DatabaseObjectRef &obj) {
  if (db_TableRef::can_wrap(obj))
    return "TABLE";

  if (db_ViewRef::can_wrap(obj))
    return "TABLE";

  if (db_mysql_RoutineRef::can_wrap(obj))
    return db_mysql_RoutineRef::cast_from(obj)->routineType();

  return "";
}

static std::string quote_user(const std::string &user) {
  std::string::size_type p;
  if ((p = user.find('@')) != std::string::npos) {
    if (user[p + 1] == '\'')
      return "'" + user.substr(0, p) + "'@" + user.substr(p + 1);
    else
      return "'" + user.substr(0, p) + "'@'" + user.substr(p + 1) + "'";
  } else
    return "'" + user + "'";
}

inline void MYSQLMODULEDBMYSQL_PUBLIC_FUNC gen_grant_sql(const db_CatalogRef &catalog, const db_UserRef &user,
                                                         db_RoleRef &role, std::list<std::string> &out,
                                                         bool ommit_schema_name = false) {
  db_RoleRef parentRole = role->parentRole();
  if (parentRole.is_valid())
    gen_grant_sql(catalog, user, parentRole, out);

  for (size_t i = 0, count = role->privileges().count(); i < count; ++i) {
    db_RolePrivilegeRef priv = role->privileges().get(i);
    std::string privilege_str;

    for (size_t i = 0, count = priv->privileges().count(); i < count; ++i) {
      if (!privilege_str.empty())
        privilege_str += ", ";
      privilege_str += priv->privileges().get(i);
    }
    if (privilege_str.empty())
      continue;

    std::string object_str;
    if (priv->databaseObjectName() == "**.*") {
      // generate the grants for all schemas in the model
      GRTLIST_FOREACH(db_Schema, catalog->schemata(), schema) {
        if (ommit_schema_name) {
          if (priv->databaseObjectType() == "SCHEMA")
            object_str = "*";
          else
            object_str = *priv->databaseObjectType() + " " + "*";
        } else {
          if (priv->databaseObjectType() == "SCHEMA")
            object_str = dbmysql::full_name(*schema) + ".*";
          else
            object_str = *priv->databaseObjectType() + " " + dbmysql::full_name(*schema) + ".*";
        }
        out.push_back("GRANT " + privilege_str + " ON " + object_str + " TO " + quote_user(*user->name()));
      }
    } else {
      db_DatabaseObjectRef object = priv->databaseObject();
      if (object.is_valid()) {
        if (db_SchemaRef::can_wrap(object))
          object_str = get_type_str_for_grant(object) + " " + dbmysql::full_name(object) + ".*";
        else
          object_str = get_type_str_for_grant(object) + " " + dbmysql::full_name(object);
      } else {
        if (priv->databaseObjectType() == "SCHEMA")
          object_str = *priv->databaseObjectName();
        else
          object_str = *priv->databaseObjectType() + " " + *priv->databaseObjectName();
      }
      if (!object_str.empty() && !(object_str == " "))
        out.push_back("GRANT " + privilege_str + " ON " + object_str + " TO " + quote_user(*user->name()));
    }
  }
}

inline void MYSQLMODULEDBMYSQL_PUBLIC_FUNC gen_grant_sql(const db_CatalogRef &catalog, const db_UserRef &user,
                                                         std::list<std::string> &out, bool ommit_schema_name = false) {
  for (size_t i = 0, count = user->roles().count(); i < count; ++i) {
    db_RoleRef role = user->roles().get(i);
    gen_grant_sql(catalog, user, role, out, ommit_schema_name);
  }
}

inline void MYSQLMODULEDBMYSQL_PUBLIC_FUNC gen_grant_sql(const db_CatalogRef &catalog, std::list<std::string> &out) {
  for (size_t i = 0, count = catalog->users().count(); i < count; ++i) {
    db_UserRef user = catalog->users().get(i);
    gen_grant_sql(catalog, user, out);
  }
}

#endif // _DB_MYSQL_DIFFSQLGEN_H_
