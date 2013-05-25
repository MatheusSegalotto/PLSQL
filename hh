WITH source_ids AS
 (SELECT *
    FROM user_identifiers
   WHERE object_name = 'SCOPE_PKG'
     AND object_type IN ('PACKAGE BODY', 'PACKAGE'))
SELECT NAME, TYPE, usage, PRIOR NAME, object_type, line, col
  FROM source_ids si
 WHERE TYPE IN ('VARIABLE', 'ITERATOR', 'CONSTANT') AND usage = 'DECLARATION' AND EXISTS(
SELECT COUNT(*), NAME
  FROM user_identifiers
 WHERE object_name = si.object_name AND NAME = si.name AND usage = si.usage
 GROUP BY NAME
HAVING COUNT(*) > 1)
 START WITH usage_context_id = 0
CONNECT BY PRIOR usage_id = usage_context_id AND PRIOR object_type = object_type;
